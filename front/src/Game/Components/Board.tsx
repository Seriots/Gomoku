import axios from 'axios';

import './Board.css';
import { useEffect } from 'react';

const CASESIZE = 36;
const BORDERSIZE = 16;

interface BoardProps {
    gameRunning: boolean,
    setGameRunning: any,
    setWinner: any,
	//gameInfo: any,
    //setGameInfo: any,
}

interface LocalGameInfoProps {
    currentPlayer: string,
    isProcessing: boolean,
    response: any,
    endGame: boolean,
    whiteCaptured: number,
    blackCaptured: number,
}

let currentPos = {
    x: 0,
    y: 0,
}


const initLocalGameInfo = () => {
    return {
        currentPlayer: 'white',
        isProcessing: false,
        response: undefined,
        endGame: false,
        whiteCaptured: 0,
        blackCaptured: 0,
    }
}

let localGameInfo: LocalGameInfoProps = initLocalGameInfo();
//let gameInfo = {
//    currentPlayer: 'white',
//    isProcessing: false,
//    gameRunning: false,
//    res: undefined,
//    winner: '',
//}

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
    const x = e.clientX - board.offsetLeft + board.offsetWidth / 2;
    const y = e.clientY - board.offsetTop + board.offsetHeight / 2;
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

    // add new stone
    for (let i = 0; i < data.added.length; i++) {
        let newStone = document.createElement('div');
        newStone.className = data.added[i].color + '-stone';
        newStone.style.left = (data.added[i].pos % 19) * CASESIZE + BORDERSIZE + 'px';
        newStone.style.top = Math.floor(data.added[i].pos / 19) * CASESIZE + BORDERSIZE + 'px';
        newStone.id = "stone-" + data.added[i].pos;
        board.appendChild(newStone);
    }

    if (localGameInfo.currentPlayer === 'white')
        localGameInfo.whiteCaptured += data.removed.length;
    else
    localGameInfo.blackCaptured += data.removed.length;

    // remove captured stone
    for (let i = 0; i < data.removed.length; i++) {
        let capturedStone = document.getElementById('stone-' + data.removed[i]);
        if (capturedStone) {
            board.removeChild(capturedStone);
        }
    }
}

const checkError = (data: any) => {
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
    } else if (data.win_by_alignement === 1) {
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

const switchColor = () => {
    localGameInfo.currentPlayer = localGameInfo.currentPlayer === 'white' ? 'black' : 'white';
}

const placeStone = async () => {

    const pos = computePositionFromPx(currentPos.x, currentPos.y);
    const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
    const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
    const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));

    await axios.get(build_request('http://localhost:6325/action', [pos, localGameInfo.currentPlayer, listWhite, listBlack, listBlocked, localGameInfo.whiteCaptured, localGameInfo.whiteCaptured]))
    .then((res) => {
        localGameInfo.response = res.data;
    })
    .catch((err) => {
        console.log(err);
    });
}

const placeIAStone = async () => {

    const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
    const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
    const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));

    await axios.get(build_request('http://localhost:6325/ia', [localGameInfo.currentPlayer, listWhite, listBlack, listBlocked, localGameInfo.whiteCaptured, localGameInfo.whiteCaptured]))
    .then((res) => {
        localGameInfo.response = res.data;
    })
    .catch((err) => {
        console.log(err);
    });
}

const handleClick = (gameRunning: any, setGameRunning: any, setWinner: any) => async (e: any) => {
    if (localGameInfo.isProcessing || !gameRunning || localGameInfo.endGame) {
        return;
    }
    const board = document.getElementById('boardID');
    if (!board) {
        return;
    }
    // place a stone at position currentPos
    localGameInfo.isProcessing = true;
    await placeStone();
    if (checkError(localGameInfo.response)) {
        localGameInfo.isProcessing = false;
        return;
    }

    responseHandler(localGameInfo.response);
    checkEndGame(localGameInfo.response, setGameRunning, setWinner);
    switchColor();
    hideShadowStone();
    if (localGameInfo.endGame || !gameRunning) {
        localGameInfo.isProcessing = false;
        return;
    }
    // generate an ia stone
    await placeIAStone();
    responseHandler(localGameInfo.response);
    checkEndGame(localGameInfo.response, setGameRunning, setWinner);
    switchColor();
    showShadowStone();
    
    localGameInfo.isProcessing = false;
}


const Board : React.FC<BoardProps> = ({
    gameRunning,
    setGameRunning,
    setWinner
    //gameInfo,
    //setGameInfo
}) => {
    useEffect(() => {
        if (gameRunning !== true)
            return ;
        localGameInfo = initLocalGameInfo();

        const board = document.getElementById('boardID');
        if (!board)
            return ;
        while (document.getElementsByClassName('white-stone').length > 0)
            board.removeChild(document.getElementsByClassName('white-stone')[0]);
        while (document.getElementsByClassName('black-stone').length > 0)
            board.removeChild(document.getElementsByClassName('black-stone')[0]);
        while (document.getElementsByClassName('blocked-stone').length > 0)
            board.removeChild(document.getElementsByClassName('blocked-stone')[0]);

    }, [gameRunning]);

    return (
        <div id='boardID' className='board' onClick={handleClick(gameRunning, setGameRunning, setWinner)} onMouseMove={handleMouseMove} onMouseEnter={handleMouseEnter(gameRunning)} onMouseLeave={handleMouseLeave}>
            <div id='shadow-stone' className='white-shadow-stone'></div>
        </div>
    );
}

export default Board;