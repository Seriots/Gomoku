#include <httplib.h>

#include <thread>
#include <mutex>
#include <vector>

#include <iostream>
#include "structs.hpp"
#include "MiniJson.hpp"

typedef struct s_population {
    std::map<e_valueDna, int> dna;
    std::string id;
    int score;
    int move_on_win;
} t_population;

typedef struct s_fight {
    int player1;
    int player2;
} t_fight;

typedef struct s_thread_info {
    std::vector<t_population> *population;
    t_fight nextFight;
    int     isWaiting;
} t_thread_info;

enum e_derivation_power {
    NOTHING,
    SMALL,
    MEDIUM,
    BIG
};

int NB_DNA = 17;
int POPULATION_NUMBER_BY_GEN = 50;
int POPULATION_SAVED = 10;

int NB_GENERATION = 10;

std::ostream& operator<<(std::ostream &os, const e_valueDna &c) {
    if (c == VDNA_ONE)
        os << "VDNA_ONE";
    else if (c == VDNA_TWON3)
        os << "VDNA_TWON3";
    else if (c == VDNA_TWON2)
        os << "VDNA_TWON2";
    else if (c == VDNA_TWON1)
        os << "VDNA_TWON1";
    else if (c == VDNA_TWO)
        os << "VDNA_TWO";
    else if (c == VDNA_THREEN2)
        os << "VDNA_THREEN2";
    else if (c == VDNA_THREEN1)
        os << "VDNA_THREEN1";
    else if (c == VDNA_THREE)
        os << "VDNA_THREE";
    else if (c == VDNA_FOURN1)
        os << "VDNA_FOURN1";
    else if (c == VDNA_FOUR)
        os << "VDNA_FOUR";
    else if (c == VDNA_THREEFREE)
        os << "VDNA_THREEFREE";
    else if (c == VDNA_FIVE)
        os << "VDNA_FIVE";
    else if (c == VDNA_POTENTIAL_CAPTURE)
        os << "VDNA_POTENTIAL_CAPTURE";
    else if (c == VDNA_EFFECTIVE_CAPTURE_0)
        os << "VDNA_EFFECTIVE_CAPTURE_0";
    else if (c == VDNA_EFFECTIVE_CAPTURE_1)
        os << "VDNA_EFFECTIVE_CAPTURE_1";
    else if (c == VDNA_EFFECTIVE_CAPTURE_2)
        os << "VDNA_EFFECTIVE_CAPTURE_2";
    else if (c == VDNA_EFFECTIVE_CAPTURE_3)
        os << "VDNA_EFFECTIVE_CAPTURE_3";
    return os;
}

int rand_weighted(std::vector<double> weights) {
    double sum = 0;
    for (auto &weight : weights) {
        sum += weight;
    }
    double random = (double)rand() / RAND_MAX;
    double sum_weights = 0;
    for (size_t i = 0; i < weights.size(); i++) {
        sum_weights += weights[i] / sum;
        if (random <= sum_weights)
            return i;
    }
    return 0;
}

std::string generateNewFilename(std::string exec_time, int generation) {
    return "logs/" + exec_time + "-gen" + std::to_string(generation);
}

void logsDna(std::string filename, std::map<e_valueDna, int> valuesMap, std::string id) {
    std::ofstream file(filename, std::ios::app);

    file << id << ": {";
    for (auto &value : valuesMap) {
        file << value.first << " : " << value.second;
        if (value.first != valuesMap.rbegin()->first)
            file << ", ";
    }
    file << "}" << std::endl;
}

void logsPopulationDna(std::string logfile, std::vector<t_population> &population) {
    for (auto &pop : population) {
        logsDna(logfile, pop.dna, pop.id);
    }
}

void logsPopulationScore(std::string logfile, std::vector<t_population> &population) {
    std::ofstream file(logfile, std::ios::app);
    file << "\n\nScores:" << std::endl;
    for (auto &pop : population) {
        file << pop.id << " : " << pop.score << " - " << (float)pop.move_on_win / (float)pop.score << std::endl;
    }
}

std::string dnaToString(std::map<e_valueDna, int> valuesMap) {
    std::string out = "";
    for (auto &value : valuesMap) {
        out += std::to_string(value.second);
        if (value.first != valuesMap.rbegin()->first)
            out += ",";
    }
    return out;
}

std::string intListToString(std::vector<int> list) {
    std::string out = "";
    for (size_t i = 0; i < list.size(); i++) {
        out += std::to_string(list[i]);
        if (i != list.size() - 1)
            out += ",";
    }
    return out;
}

std::map<e_valueDna, int> generateValuesMaps(std::vector<int> values) {
    std::map<e_valueDna, int> valuesMap;

    for (size_t i = 0; i < values.size(); i++) {
        valuesMap[(e_valueDna)i] = values[i];
    }
    return valuesMap;
}

std::string generateRandomId() {
    std::string id = "";
    std::string charset = "abcdefghijklmnopqrstuvwxyz";
    std::string intset = "0123456789";
    for (size_t i = 0; i < 7; i++) {
        id += charset[rand() % charset.size()];
    }
    id += "-";
    for (size_t i = 0; i < 16; i++) {
        id += intset[rand() % intset.size()];
    }
    return id;
}


std::vector<int> generateRandonDna() {
    std::vector<int> dna(NB_DNA);

    dna[0] = rand() % 5;
    dna[1] = rand() % 30;
    dna[2] = rand() % 50;
    dna[3] = rand() % 80;
    dna[4] = rand() % 120;
    dna[5] = rand() % 320;
    dna[6] = rand() % 500;
    dna[7] = rand() % 2000;
    dna[8] = rand() % 4000;
    dna[9] = rand() % 8000;
    dna[10] = rand() % 15000;
    dna[11] = rand() % 1000000;
    dna[12] = rand() % 5000;
    dna[13] = rand() % 20000;
    dna[14] = rand() % 20000;
    dna[15] = rand() % 20000;
    dna[16] = rand() % 1000000;

    return dna;
}

std::vector<int> generateDnaFromParents(std::map<e_valueDna, int> &parent1, std::map<e_valueDna, int> &parent2, e_derivation_power power) {
    std::vector<int> dna(NB_DNA);

    for (int i = 0; i < NB_DNA; i++) {
        dna[i] = rand() % 2 ? parent1[(e_valueDna)i] : parent2[(e_valueDna)i];
        if (power == SMALL)
            dna[i] *= 1 + (float)((rand() % 20) - 10) / 100;
        else if (power == MEDIUM)
            dna[i] *= 1 + (float)((rand() % 80) - 40) / 100;
        else if (power == BIG)
            dna[i] *= 1 + (float)((rand() % 400) - 200) / 100;        
    }
    return dna;
}

void sortPopulation(std::vector<t_population> &population) {
    std::sort(population.begin(), population.end(), [](t_population a, t_population b) {
        if (a.score == b.score)
            return a.move_on_win < b.move_on_win;
        return a.score > b.score;
    });
}

std::vector<t_population> generatePopulationsGenZero() {
    std::vector<t_population> population(POPULATION_NUMBER_BY_GEN);

    for (int i = 0; i < POPULATION_NUMBER_BY_GEN; i++) {
        population[i].dna = generateValuesMaps(generateRandonDna());
        population[i].id = generateRandomId();
        population[i].score = 0;
    }
    
    return population;
}

std::vector<t_population> generatePopulationFromLastGen(std::vector<t_population> &lastGen) {
    std::vector<t_population> population(POPULATION_NUMBER_BY_GEN);
    

    for (int i = 0; i < POPULATION_SAVED; i++) {
        population[i].dna = lastGen[i].dna;
        population[i].id = lastGen[i].id;
        population[i].score = 0;
    }
    
    t_population parent1;
    t_population parent2;
    e_derivation_power power;

    for (int i = POPULATION_SAVED; i < POPULATION_NUMBER_BY_GEN; i++) {
        population[i].id = generateRandomId();
        parent1 = lastGen[rand() % POPULATION_SAVED];
        parent2 = lastGen[rand() % POPULATION_SAVED];
        power = (e_derivation_power)(rand_weighted({0.4, 0.3, 0.2, 0.1}));
        population[i].dna = generateValuesMaps(generateDnaFromParents(parent1.dna, parent2.dna, power));
        population[i].score = 0;
    }
    return population;
}

std::vector<t_population> generatePopulation(int gen, std::vector<t_population> &lastGen) {
    if (gen == 0) 
        return generatePopulationsGenZero();
    else
        return generatePopulationFromLastGen(lastGen);
}

void fight(t_population &player1, t_population &player2) {

    httplib::Client     cli("localhost", 6325);
    std::vector<int>    player1_stones;
    std::vector<int>    player2_stones;
    httplib::Result     res;
    std::string         color;
    MiniJson            json;
    int                 moveCounter = 0;

    color = "white";
    //std::cout << "Player1: " << player1.id << " vs Player2: " << player2.id << std::endl;
    while (true) {
        std::string req = "/iaWithDna/" + color + "/" + intListToString(player1_stones) + "/" + intListToString(player2_stones) + "//0/0/" + (color == "white" ? dnaToString(player1.dna) : dnaToString(player2.dna)) + "/";
        res = cli.Get(req.c_str());

        json.parse(res->body);
        moveCounter++;

        if (json.getInt("win_by_alignement") == 1) {
            color == "white" ? player1.score += 1 : player2.score += 1;
            color == "white" ? player1.move_on_win += moveCounter : player2.move_on_win += moveCounter;
            break;
        }
        if (json.getInt("no_winner") == 1) {
            break;
        }
        color == "white" ? player1_stones.push_back(json.getStoneList("added")[0].pos) : player2_stones.push_back(json.getStoneList("added")[0].pos);
        color = color == "white" ? "black" : "white";
    }
    //std::cout << "Player1: " << player1.score << " Player2: " << player2.score << std::endl;
}

void versus(t_population &player1, t_population &player2) {
    fight(player1, player2);
    fight(player2, player1);
}

void firstPhase(std::vector<t_population> &population) {
    std::vector<t_fight>        fights;
    std::vector<std::thread>    threadPool;

    for (size_t i = 0; i < population.size(); i+=2) {
        fights.push_back({(int)i, (int)i + 1});
    }
    for (int i = 0; i < POPULATION_NUMBER_BY_GEN - 2; i++) {
        for (int j = 0; j < POPULATION_NUMBER_BY_GEN / 2; j++) {
            if (j == 0) {
                fights.push_back({fights[i * POPULATION_NUMBER_BY_GEN / 2 + j].player1, fights[i * POPULATION_NUMBER_BY_GEN / 2 + j + 1].player1});
            } else if (j == POPULATION_NUMBER_BY_GEN / 2 - 1) {
                fights.push_back({fights[i * POPULATION_NUMBER_BY_GEN / 2 + j].player2, fights[i * POPULATION_NUMBER_BY_GEN / 2 + j - 1].player2});
            } else {
                fights.push_back({fights[i * POPULATION_NUMBER_BY_GEN / 2 + j + 1].player1, fights[i * POPULATION_NUMBER_BY_GEN / 2 + j - 1].player2});
            }
        }
    }

    for (int round = 0; round < POPULATION_NUMBER_BY_GEN - 1; round++) {
        std::cout << "Fight: " << round + 1 << std::endl;
        for (int i = 0; i < POPULATION_NUMBER_BY_GEN / 2; i++) {
            std::thread thread_object (versus, std::ref(population[fights[i].player1]), std::ref(population[fights[i].player2]));
            threadPool.push_back(std::move(thread_object));
        }
        for (auto &thread : threadPool) {
            thread.join();
        }
        threadPool.clear();
        fights.erase(fights.begin(), fights.begin() + POPULATION_NUMBER_BY_GEN / 2);
    }

}
// void threadProcess(std::vector<t_fight> fights, std::vector<t_population> &population, std::mutex &mutexFights) {
//     (void)population;
//     mutexFights.lock();
//     while (fights.size() != 0) {
//         t_fight fight = fights[0];
//         fights.erase(fights.begin());
//         sleep(500);
//         std::cout << "End: "<< fight.player1 << " vs " << fight.player2 << std::endl;
//         mutexFights.unlock();  
//     }
// }

void secondPhase(std::vector<t_population> &population) {
    std::mutex                      m;
    std::vector<t_fight>            fights;
    std::vector<std::thread>        threads;
    std::vector<std::mutex>         playerMutexes(POPULATION_NUMBER_BY_GEN);

    for (size_t i = 0; i < population.size(); i+=2) {
        fights.push_back({(int)i, (int)i + 1});
    }
    for (int i = 0; i < POPULATION_NUMBER_BY_GEN - 2; i++) {
        for (int j = 0; j < POPULATION_NUMBER_BY_GEN / 2; j++) {
            if (j == 0) {
                fights.push_back({fights[i * POPULATION_NUMBER_BY_GEN / 2 + j].player1, fights[i * POPULATION_NUMBER_BY_GEN / 2 + j + 1].player1});
            } else if (j == POPULATION_NUMBER_BY_GEN / 2 - 1) {
                fights.push_back({fights[i * POPULATION_NUMBER_BY_GEN / 2 + j].player2, fights[i * POPULATION_NUMBER_BY_GEN / 2 + j - 1].player2});
            } else {
                fights.push_back({fights[i * POPULATION_NUMBER_BY_GEN / 2 + j + 1].player1, fights[i * POPULATION_NUMBER_BY_GEN / 2 + j - 1].player2});
            }
        }
    }

    auto processThread = [&m, &playerMutexes](std::vector<t_population> &population, std::vector<t_fight> &fights) {
        m.lock();
        while (fights.size() != 0) {
            t_fight ft = fights[0];
            fights.erase(fights.begin());

            std::cout << "Start: "<< ft.player1 << " vs " << ft.player2 << "--" << fights.size()<< std::endl;
            m.unlock();
            if (ft.player1 > ft.player2){
                playerMutexes[ft.player1].lock();
                playerMutexes[ft.player2].lock();
            } else {
                playerMutexes[ft.player2].lock();
                playerMutexes[ft.player1].lock();
            }
            versus(population[ft.player1], population[ft.player2]);
            if (ft.player1 > ft.player2){
                playerMutexes[ft.player2].unlock();
                playerMutexes[ft.player1].unlock();
            } else {
                playerMutexes[ft.player1].unlock();
                playerMutexes[ft.player2].unlock();
            }
            m.lock();
        }
        m.unlock();
    };

    for (int i = 0; i < POPULATION_NUMBER_BY_GEN / 2; i++) {
        if (i == 1)
            threads.push_back(std::thread(processThread, std::ref(population), std::ref(fights)));
        else 
            threads.push_back(std::thread(processThread, std::ref(population), std::ref(fights)));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    threads.clear();


}

void train(std::vector<t_population> &population) {
    secondPhase (population);
}

void create_directory(std::string name) {
    std::string command = "mkdir -p " + name;
    system(command.c_str());
}

int main() {
    std::vector<t_population>   population;
    std::string                 exec_time;
    std::string                 logfile;

    srand(time(NULL));

    create_directory("logs");
    
    exec_time = std::to_string(time(NULL));

    for (int i = 0; i < NB_GENERATION; i++) {
        logfile = generateNewFilename(exec_time, i);
        population = generatePopulation(i, population);
        logsPopulationDna(logfile, population);
        train(population);
        sortPopulation(population);
        logsPopulationScore(logfile, population);
    }


    return 0;
}