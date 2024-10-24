import { useState } from 'react';
import Board from './Components/Board';
import BoardShadow from './Components/BoardShadow';
import InfoBar from './Components/InfoBar';
import ParamsBar from './Components/ParamsBar';
import './GameIA.css';
import StartButton from './Components/StartButton';

export interface GameInfoInterface {
    currentPlayer: string,
    currentRound: number,
    whiteCaptured: number,
    blackCaptured: number,
    processTime: number,
    processDepth: number,
}

const GameIn : GameInfoInterface = {
    currentPlayer: 'white',
    currentRound: 0,
    whiteCaptured: 0,
    blackCaptured: 0,
    processTime: 0,
    processDepth: 0,
}

function GameIA() {
    const [gameRunning, setGameRunning] = useState(false);
    const [winner, setWinner] = useState('');
    const [gameInfo, setGameInfo] = useState(GameIn);
    const [firstPlayer, setFirstPlayer] = useState('white');

    return (
        <div className='gameIA-master'>
            <ParamsBar  setFirstPlayer={setFirstPlayer}/>
            <InfoBar gameInfo={gameInfo}/>
            <Board gameRunning={gameRunning} setGameRunning={setGameRunning} setWinner={setWinner} gameInfo={gameInfo} setGameInfo={setGameInfo} firstPlayer={firstPlayer}/>
            <BoardShadow gameRunning={gameRunning} winner={winner} setWinner={setWinner}/>
            <StartButton gameRunning={gameRunning} setGameRunning={setGameRunning} />
        </div>
    );
}

export default GameIA;