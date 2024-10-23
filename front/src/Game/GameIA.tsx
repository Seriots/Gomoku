import { useState } from 'react';
import Board from './Components/Board';
import BoardShadow from './Components/BoardShadow';
import InfoBar from './Components/InfoBar';
import ParamsBar from './Components/ParamsBar';
import './GameIA.css';
import StartButton from './Components/StartButton';


function GameIA() {
    const [gameRunning, setGameRunning] = useState(false);
    const [winner, setWinner] = useState('');
    //const [gameInfo, setGameInfo] = useState(undefined);

    return (
        <div className='gameIA-master'>
            <ParamsBar />
            <InfoBar />
            <Board gameRunning={gameRunning} setGameRunning={setGameRunning} setWinner={setWinner}/>
            <BoardShadow gameRunning={gameRunning} winner={winner} setWinner={setWinner}/>
            <StartButton gameRunning={gameRunning} setGameRunning={setGameRunning} />
        </div>
    );
}

export default GameIA;