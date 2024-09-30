import axios from 'axios';

function Game() {
    const test = async () => {
        const res = await axios.get('http://localhost:6325/game');
        console.log(res.data);
    }

    return (
        <div>
            <h1>Game</h1>
        </div>
    );
}

export default Game;