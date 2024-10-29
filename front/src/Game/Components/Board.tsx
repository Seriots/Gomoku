import axios from 'axios';

import './Board.css';
import { GameInfoInterface } from '../GameIA';
import { useEffect, useState } from 'react';

const CASESIZE = 36;
const BORDERSIZE = 16;

interface BoardProps {
    gameRunning: boolean,
    setGameRunning: any,
    setWinner: any,
    gameInfo: GameInfoInterface,
    setGameInfo: any,
    firstPlayer: any,
    IAMode: boolean,
    activateHintP1?: boolean,
    activateHintP2?: boolean,
}

interface LocalGameInfoProps {
    currentPlayer: string,
    isProcessing: boolean,
    response: any,
    endGame: boolean,
    whiteCapture: number,
    blackCapture: number,
    listAllowed: string,
    moveCount: number,
}

let currentPos = {
    x: 0,
    y: 0,
}


const initLocalGameInfo = (firstPlayer: string) => {
    return {
        currentPlayer: firstPlayer,
        isProcessing: false,
        response: undefined,
        endGame: false,
        whiteCapture: 0,
        blackCapture: 0,
        listAllowed: '',
        moveCount: 0,
    }
}

let localGameInfo: LocalGameInfoProps = initLocalGameInfo('white');

const build_request = (base: string, lst: any) => {
    let res = base;
    for (let i = 0; i < lst.length; i++) {
        res += '/' + lst[i];
    }
    return res;
}

const setCurrentPos = (x: number, y: number) => {
    currentPos = {
        x: x,
        y: y,
    }
}

const computePositionFromPx = (x: number, y: number) => {
    const posX = (x - BORDERSIZE) / CASESIZE;
    const posY = (y - BORDERSIZE) / CASESIZE;
    return posX + posY * 19;
}

const getPositionList = (lst: any) => {
    let res = [];
    for (let i = 0; i < lst.length; i++) {
        res.push(computePositionFromPx(parseInt(lst[i].style.left), parseInt(lst[i].style.top)));
    }
    return res.join(',');
}

const handleMouseMove = (e: any) => {
    const board = document.getElementById('boardID');
    const shadowStone = document.getElementById('shadow-stone');
    if (!board || !shadowStone) {
        return;
    }
    const x = e.clientX - board.offsetLeft + board.offsetWidth * 0.5 + window.scrollX;
    const y = e.clientY - board.offsetTop + board.offsetHeight * 0.6 + window.scrollY;
    const nearestX = Math.floor(x / CASESIZE) * CASESIZE + BORDERSIZE;
    const nearestY = Math.floor(y / CASESIZE) * CASESIZE + BORDERSIZE;
    setCurrentPos(nearestX, nearestY);
    shadowStone.style.left = nearestX + 'px';
    shadowStone.style.top = nearestY + 'px';
}

const handleMouseEnter = (gameRunning: boolean) => (e: any) => {
    if (!gameRunning) {
        return;
    }

    const shadowStone = document.getElementById('shadow-stone');
    if (shadowStone) {
        shadowStone.style.display = 'block';
    }
}

const handleMouseLeave = (e: any) => {
    const shadowStone = document.getElementById('shadow-stone');
    if (shadowStone) {
        shadowStone.style.display = 'none';
    }
}

const responseHandler = (data: any) => {
    const board = document.getElementById('boardID');
    if (!board)
        return;

    // remove blocked stone
    while (document.getElementsByClassName('blocked-stone').length > 0) {
        board.removeChild(document.getElementsByClassName('blocked-stone')[0]);
    }

    while (document.getElementsByClassName('allowed-stone').length > 0) {
        board.removeChild(document.getElementsByClassName('allowed-stone')[0]);
    }

    // add new stone
    for (let i = 0; i < data.added.length; i++) {
        let newStone = document.createElement('div');
        newStone.className = data.added[i].color + '-stone';
        newStone.style.left = (data.added[i].pos % 19) * CASESIZE + BORDERSIZE + 'px';
        newStone.style.top = Math.floor(data.added[i].pos / 19) * CASESIZE + BORDERSIZE + 'px';
        newStone.id = "stone-" + data.added[i].pos;
        board.appendChild(newStone);
    }

    for (let i = 0; i < data.prevent_win.length; i++) {
        let newStone = document.createElement('div');
        newStone.className = 'allowed-stone';
        newStone.style.left = (data.prevent_win[i] % 19) * CASESIZE + BORDERSIZE + 'px';
        newStone.style.top = Math.floor(data.prevent_win[i] / 19) * CASESIZE + BORDERSIZE + 'px';
        newStone.id = "allowed-stone-" + data.prevent_win[i];
        board.appendChild(newStone);
    }

    if (localGameInfo.currentPlayer === 'white')
        localGameInfo.whiteCapture += data.removed.length;
    else
        localGameInfo.blackCapture += data.removed.length;

    // remove captured stone
    for (let i = 0; i < data.removed.length; i++) {
        let capturedStone = document.getElementById('stone-' + data.removed[i]);
        if (capturedStone) {
            board.removeChild(capturedStone);
        }
    }

    if (data.prevent_win.length > 0) {
        localGameInfo.listAllowed = data.prevent_win.join(',');
    } else {
        localGameInfo.listAllowed = '';
    }
}

const checkError = (data: any) => {
    if (data === undefined) {
        console.log('Error: no response');
        return true;
    }
    if (data.error !== undefined) {
        console.log(data.error);
        return true;
    }
    return false;
}

const checkEndGame = (data: any, setGameRunning: any, setWinner: any) => {
    if (data.win_by_capture === 1) {
        setWinner(localGameInfo.currentPlayer);
        setGameRunning(false);
        localGameInfo.endGame = true;
        console.log(localGameInfo.currentPlayer + ' win by capture');
    } else if (data.win_by_alignement === 1 && data.prevent_win.length === 0) {
        setWinner(localGameInfo.currentPlayer);
        setGameRunning(false);
        localGameInfo.endGame = true;
        console.log(localGameInfo.currentPlayer + ' win by alignement');
    } else if (data.no_winner === 1) {
        setWinner('Draw')
        setGameRunning(false);
        localGameInfo.endGame = true;
        console.log('No winner');
    }
}

const hideShadowStone = () => {
    const shadowStone = document.getElementById('shadow-stone');
    if (shadowStone) {
        shadowStone.style.display = 'none';
    }
}

const showShadowStone = () => {
    const shadowStone = document.getElementById('shadow-stone');
    if (shadowStone) {
        shadowStone.style.display = 'block';
    }
}

const swapColorShadowStone = () => {
    const shadowStone = document.getElementById('shadow-stone');
    if (shadowStone) {
        shadowStone.className = localGameInfo.currentPlayer === 'white' ? 'white-shadow-stone' : 'black-shadow-stone';
    }
}

const switchColor = () => {
    localGameInfo.currentPlayer = localGameInfo.currentPlayer === 'white' ? 'black' : 'white';
}

const getStone = async () => {
    const hintStone = document.getElementById('hint-stone');
    if (hintStone)
        hintStone.style.display = 'none';

    const pos = computePositionFromPx(currentPos.x, currentPos.y);
    const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
    const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
    const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));

    console.log("lstWhite: ", listWhite, " lstBlack: ", listBlack);

    await axios.get(build_request('http://localhost:6325/action', [pos, localGameInfo.currentPlayer, listWhite, listBlack, listBlocked, localGameInfo.listAllowed, localGameInfo.whiteCapture, localGameInfo.blackCapture]))
    .then((res) => {
        localGameInfo.response = res.data;
        localGameInfo.moveCount++;
    })
    .catch((err) => {
        console.log(err);
    });
}

const getIaStone = async (IAMode: boolean) => {

    const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
    const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
    const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));
    console.log("lstWhite: ", listWhite, " lstBlack: ", listBlack);

    await axios.get(build_request('http://localhost:6325/ia', [localGameInfo.currentPlayer, listWhite, listBlack, listBlocked, localGameInfo.listAllowed, localGameInfo.whiteCapture, localGameInfo.blackCapture]))
    .then((res) => {
        localGameInfo.response = res.data;
        localGameInfo.moveCount++;
        if (!IAMode) {
            setHintIAStone(localGameInfo.response);
        }
    })
    .catch((err) => {
        console.log(err);
    });
}

const updateGameInfo = (data: any, gameInfo: GameInfoInterface, setGameInfo: any) => {
    const time = data.time === undefined ? gameInfo.processTime : data.time;
    const depth = data.depthSearch === undefined ? gameInfo.processDepth : data.depthSearch;


    const newGameInfo: GameInfoInterface = {
        currentPlayer: localGameInfo.currentPlayer,
        currentRound: localGameInfo.moveCount,
        whiteCapture: localGameInfo.whiteCapture,
        blackCapture: localGameInfo.blackCapture,
        processTime: time,
        processDepth: depth,
    }
    setGameInfo(newGameInfo);
}

const setHintIAStone = (data: any) => {
    const hintStone = document.getElementById('hint-stone');
    if (!hintStone)
        return;

    const pos = data.added[0].pos;
    console.log(pos);
    hintStone.style.left = (pos % 19) * CASESIZE + BORDERSIZE + 'px';
    hintStone.style.top = Math.floor(pos / 19) * CASESIZE + BORDERSIZE + 'px';
    hintStone.className = localGameInfo.currentPlayer === 'white' ? 'white-hint-stone' : 'black-hint-stone';
    hintStone.style.display = 'block';
}


const handleClick = (IAMode: boolean, gameRunning: any, setGameRunning: any, setWinner: any, gameInfo: GameInfoInterface, setGameInfo: any, activateHintP1?: boolean, activateHintP2?: boolean) => async (e: any) => {
    if (localGameInfo.isProcessing || !gameRunning || localGameInfo.endGame) {
        return;
    }
    const board = document.getElementById('boardID');
    if (!board) {
        return;
    }
    // place a stone at position currentPos
    localGameInfo.isProcessing = true;
    await getStone();
    if (checkError(localGameInfo.response)) {
        localGameInfo.isProcessing = false;
        return;
    }

    responseHandler(localGameInfo.response);
    checkEndGame(localGameInfo.response, setGameRunning, setWinner);
    switchColor();
    updateGameInfo(localGameInfo.response, gameInfo, setGameInfo);
    if (IAMode) {
        hideShadowStone();
    } else {
        swapColorShadowStone();
    }
    if (localGameInfo.endGame || !gameRunning) {
        localGameInfo.isProcessing = false;
        return;
    }

    if (IAMode) {
        // generate an ia stone
        await getIaStone(IAMode);
        if (checkError(localGameInfo.response)) {
            localGameInfo.isProcessing = false;
            return;
        }
        responseHandler(localGameInfo.response);
        checkEndGame(localGameInfo.response, setGameRunning, setWinner);
        switchColor();
        updateGameInfo(localGameInfo.response, gameInfo, setGameInfo);
        showShadowStone();
    }
    localGameInfo.isProcessing = false;

    if (!IAMode && ((activateHintP1 && localGameInfo.currentPlayer === 'white') || (activateHintP2 && localGameInfo.currentPlayer === 'black'))) {
        getIaStone(IAMode);
    }
}

const sleep = (ms: number) => {
    return new Promise(resolve => setTimeout(resolve, ms));
}

const Board : React.FC<BoardProps> = ({
    gameRunning,
    setGameRunning,
    setWinner,
    gameInfo,
    setGameInfo,
    firstPlayer,
    IAMode,
    activateHintP1,
    activateHintP2,
}) => {
    const [runFirstIa, setRunFirstIa] = useState(false);

    useEffect(() => {
        const playIa = async () => {
            localGameInfo.isProcessing = true;
            while (true) {
                await getIaStone(IAMode);
                if (!checkError(localGameInfo.response)) {
                    break;
                }
                sleep(1000);
            }
            responseHandler(localGameInfo.response);
            checkEndGame(localGameInfo.response, setGameRunning, setWinner);
            switchColor();
            updateGameInfo(localGameInfo.response, gameInfo, setGameInfo);
            swapColorShadowStone();
            showShadowStone();

            localGameInfo.isProcessing = false;
        }
        if (runFirstIa) {
            setRunFirstIa(false);
            playIa();
        }
    }
    , [runFirstIa, gameInfo, setGameInfo, setGameRunning, setWinner, IAMode]);

    useEffect(() => {
        if (gameRunning !== true)
            return ;
        localGameInfo = initLocalGameInfo(firstPlayer.current);

        const board = document.getElementById('boardID');
        if (!board)
            return ;
        while (document.getElementsByClassName('white-stone').length > 0)
            board.removeChild(document.getElementsByClassName('white-stone')[0]);
        while (document.getElementsByClassName('black-stone').length > 0)
            board.removeChild(document.getElementsByClassName('black-stone')[0]);
        while (document.getElementsByClassName('blocked-stone').length > 0)
            board.removeChild(document.getElementsByClassName('blocked-stone')[0]);

        const shadowStone = document.getElementById('shadow-stone');
        if (shadowStone)
            shadowStone.className = firstPlayer.current === 'white' ? 'white-shadow-stone' : 'black-shadow-stone';

        const hintStone = document.getElementById('hint-stone');
        if (hintStone)
            hintStone.className = firstPlayer.current === 'white' ? 'white-hint-stone' : 'black-hint-stone';

        if (firstPlayer.current === 'black') {
            setRunFirstIa(true);
        }

    }, [gameRunning, firstPlayer]);

    return (
        <div id='boardID' className='board' onClick={handleClick(IAMode, gameRunning, setGameRunning, setWinner, gameInfo, setGameInfo, activateHintP1, activateHintP2)} onMouseMove={handleMouseMove} onMouseEnter={handleMouseEnter(gameRunning)} onMouseLeave={handleMouseLeave}>
            <div id='shadow-stone' className='white-shadow-stone'></div>
            <div id='hint-stone' className='white-hint-stone'></div>
        </div>
    );
}

export default Board;
