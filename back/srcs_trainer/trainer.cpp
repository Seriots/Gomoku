#include <httplib.h>

#include <iostream>
#include "structs.hpp"

typedef struct s_population {
    std::map<e_valueDna, int> dna;
    std::string id;
    int score;
} t_population;

int NB_DNA = 16;
int POPULATION_NUMBER_BY_GEN = 50;
int SCORE_THRESHOLD = 40;
int POPULATION_SAVED = 10;

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
        file << pop.id << " : " << pop.score << std::endl;
    }
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


std::vector<int> generateRandonDna(int nbDna) {
    std::vector<int> dna(nbDna);

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
    dna[10] = rand() % 1000000;
    dna[11] = rand() % 5000;
    dna[12] = rand() % 20000;
    dna[13] = rand() % 20000;
    dna[14] = rand() % 20000;
    dna[15] = rand() % 1000000;

    return dna;
}

std::vector<t_population> generatePopulationsGenZero(int populationSize, int nbDna) {
    std::vector<t_population> population(populationSize);

    for (int i = 0; i < populationSize; i++) {
        population[i].dna = generateValuesMaps(generateRandonDna(nbDna));
        population[i].id = generateRandomId();
        population[i].score = 0;
    }
    
    return population;
}

void train(std::vector<t_population> &population, int populationSize) {
    for (int i = 0; i < populationSize; i++) {
        for (int dna = 0; dna < NB_DNA - 6; dna++) {
            population[i].score += population[i].dna[(e_valueDna)dna];
        }
    }

}

int main() {
    std::string exec_time = std::to_string(time(NULL));
    srand(time(NULL));
    std::map<std::string, int> gen_records;

    std::string logfile = generateNewFilename(exec_time, 0);
    std::vector<t_population> population = generatePopulationsGenZero(POPULATION_NUMBER_BY_GEN, NB_DNA);
    logsPopulationDna(logfile, population);

    train(population, POPULATION_NUMBER_BY_GEN);
    std::sort(population.begin(), population.end(), [](t_population a, t_population b) {
        return a.score > b.score;
    });
    logsPopulationScore(logfile, population);

    // crossover
    // mutate
    // repeat
    return 0;
}