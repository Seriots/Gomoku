import { useEffect, useRef, useState } from "react";
import ParamsBar from "./Components/ParamsBar";
import InfoBar from "./Components/InfoBar";
import Board from "./Components/Board";
import BoardShadow from "./Components/BoardShadow";
import StartButton from "./Components/StartButton";
import { GameInfoInterface } from "./GameIA";
import ActivateHintProp from "./Components/ActivateHintProp";
import './GameStyle.css';
import DepthProp from "./Components/DepthProp";

const GameIn: GameInfoInterface = {
    currentPlayer: 'white',
    currentRound: 0,
    whiteCapture: 0,
    blackCapture: 0,
    processTime: 0,
    processDepth: 0,
}

function GameIA() {
    const [gameRunning, setGameRunning] = useState(false);
    const [winner, setWinner] = useState('');
    const [gameInfo, setGameInfo] = useState(GameIn);
    const [activateHintP1, setActivateHintP1] = useState(false);
    const [activateHintP2, setActivateHintP2] = useState(false);
    const [depth, setDepth] = useState(5);
    const firstPlayerRef = useRef('white');

    useEffect(() => {
        if (gameRunning === true) {
            setGameInfo(GameIn);
            firstPlayerRef.current = 'white';
        }
    }, [gameRunning]);

    return (
        <div className='gameIA-master'>
            <ParamsBar labels={['Hint Player 1', 'Hint Player 2', 'Depth']}>
                <ActivateHintProp activateHint={activateHintP1} setActivateHint={setActivateHintP1} gameRunning={gameRunning} id='1' />
                <ActivateHintProp activateHint={activateHintP2} setActivateHint={setActivateHintP2} gameRunning={gameRunning} id='2' />
                <DepthProp depth={depth} setDepth={setDepth} gameRunning={gameRunning} />
            </ParamsBar>
            <InfoBar gameInfo={gameInfo} />
            <Board IAMode={false} gameRunning={gameRunning} setGameRunning={setGameRunning} setWinner={setWinner} gameInfo={gameInfo} setGameInfo={setGameInfo} firstPlayer={firstPlayerRef} activateHintP1={activateHintP1} activateHintP2={activateHintP2}/>
            <BoardShadow gameRunning={gameRunning} winner={winner} setWinner={setWinner}/>
            <StartButton gameRunning={gameRunning} setGameRunning={setGameRunning} />
        </div>
    );
}

export default GameIA;
