import { useEffect, useRef, useState } from 'react';
import Board from './Components/Board';
import BoardShadow from './Components/BoardShadow';
import InfoBar from './Components/InfoBar';
import ParamsBar from './Components/ParamsBar';
import './GameStyle.css';
import StartButton from './Components/StartButton';
import FirstPlayerProp from './Components/FirstPlayerProp';

export interface GameInfoInterface {
    currentPlayer: string,
    currentRound: number,
    whiteCaptured: number,
    blackCaptured: number,
    processTime: number,
    processDepth: number,
}

const GameInWhite: GameInfoInterface = {
    currentPlayer: 'white',
    currentRound: 0,
    whiteCaptured: 0,
    blackCaptured: 0,
    processTime: 0,
    processDepth: 0,
}

const GameInBlack: GameInfoInterface = {
    currentPlayer: 'black',
    currentRound: 0,
    whiteCaptured: 0,
    blackCaptured: 0,
    processTime: 0,
    processDepth: 0,
}

function GameIA() {
    const [gameRunning, setGameRunning] = useState(false);
    const [winner, setWinner] = useState('');
    const [gameInfo, setGameInfo] = useState(GameInWhite);
    const [firstPlayer, setFirstPlayer] = useState('white');
    const firstPlayerRef = useRef(firstPlayer);

    useEffect(() => {
        if (firstPlayer === 'white')
            setGameInfo(GameInWhite);
        else
            setGameInfo(GameInBlack);
        firstPlayerRef.current = firstPlayer;
    }, [firstPlayer]);

    return (
        <div className='gameIA-master'>
            <ParamsBar labels={['First Player', 'second']}>
                <FirstPlayerProp firstPlayer={firstPlayer} setFirstPlayer={setFirstPlayer} gameRunning={gameRunning} />
            </ParamsBar>
            <InfoBar gameInfo={gameInfo}/>
            <Board IAMode={true} gameRunning={gameRunning} setGameRunning={setGameRunning} setWinner={setWinner} gameInfo={gameInfo} setGameInfo={setGameInfo} firstPlayer={firstPlayerRef}/>
            <BoardShadow gameRunning={gameRunning} winner={winner} setWinner={setWinner}/>
            <StartButton gameRunning={gameRunning} setGameRunning={setGameRunning} />
        </div>
    );
}

export default GameIA;