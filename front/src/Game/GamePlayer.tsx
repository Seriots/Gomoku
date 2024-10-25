import { useEffect, useRef, useState } from "react";
import ParamsBar from "./Components/ParamsBar";
import InfoBar from "./Components/InfoBar";
import Board from "./Components/Board";
import BoardShadow from "./Components/BoardShadow";
import StartButton from "./Components/StartButton";
import { GameInfoInterface } from "./GameIA";

const GameIn: GameInfoInterface = {
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
    const firstPlayerRef = useRef('white');

    useEffect(() => {
        if (gameRunning === true) {
            setGameInfo(GameIn);
            firstPlayerRef.current = 'white';
        }
    }, [gameRunning]);

    return (
        <div className='gameIA-master'>
            {/* <ParamsBar  firstPlayer={firstPlayer} setFirstPlayer={setFirstPlayer} gameRunning={gameRunning}/> */}
            <InfoBar gameInfo={gameInfo}/>
            <Board IAMode={false} gameRunning={gameRunning} setGameRunning={setGameRunning} setWinner={setWinner} gameInfo={gameInfo} setGameInfo={setGameInfo} firstPlayer={firstPlayerRef}/>
            <BoardShadow gameRunning={gameRunning} winner={winner} setWinner={setWinner}/>
            <StartButton gameRunning={gameRunning} setGameRunning={setGameRunning} />
        </div>
    );
}

export default GameIA;