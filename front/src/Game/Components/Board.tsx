import axios from 'axios';

import './Board.css';

interface BoardProps {
	label?: string,
}

let currentPos = {
    x: 0,
    y: 0,
}

let gameInfo = {
    currentPlayer: 'white',
    isProcessing: false,
    endGame: false,
}

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
    const posX = (x - 21) / 48;
    const posY = (y - 21) / 48;
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
    const nearestX = Math.floor(x / 48) * 48 + 21;
    const nearestY = Math.floor(y / 48) * 48 + 21;
    setCurrentPos(nearestX, nearestY);
    shadowStone.style.left = nearestX + 'px';
    shadowStone.style.top = nearestY + 'px';
}

const handleMouseEnter = (e: any) => {
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

const responseHandler = (res: any) => {
    const board = document.getElementById('boardID');
    if (!board)
        return;

    // remove blocked stone
    while (document.getElementsByClassName('blocked-stone').length > 0) {
        board.removeChild(document.getElementsByClassName('blocked-stone')[0]);
    }

    // add new stone
    for (let i = 0; i < res.data.added.length; i++) {
        let newStone = document.createElement('div');
        newStone.className = res.data.added[i].color + '-stone';
        newStone.style.left = (res.data.added[i].pos % 19) * 48 + 21 + 'px';
        newStone.style.top = Math.floor(res.data.added[i].pos / 19) * 48 + 21 + 'px';
        newStone.id = "stone-" + res.data.added[i].pos;
        board.appendChild(newStone);
    }

    // remove captured stone
    for (let i = 0; i < res.data.removed.length; i++) {
        let capturedStone = document.getElementById('stone-' + res.data.removed[i]);
        if (capturedStone) {
            board.removeChild(capturedStone);
        }
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

const placeStone = async () => {

    const pos = computePositionFromPx(currentPos.x, currentPos.y);
    const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
    const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
    const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));

    await axios.get(build_request('http://localhost:6325/action', [pos, gameInfo.currentPlayer, listWhite, listBlack, listBlocked]))
    .then((res) => {
        console.log(res.data);
        responseHandler(res);
    })
    .catch((err) => {
        console.log(err);
    });
}

const placeIAStone = async () => {

    const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
    const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
    const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));

    await axios.get(build_request('http://localhost:6325/ia', [gameInfo.currentPlayer, listWhite, listBlack, listBlocked, 0, 0]))
    .then((res) => {
        console.log(res.data);
        responseHandler(res);
    })
    .catch((err) => {
        console.log(err);
    });
}

const handleClick = async (e: any) => {
    if (gameInfo.isProcessing || gameInfo.endGame) {
        return;
    }
    const board = document.getElementById('boardID');
    if (!board) {
        return;
    }
    // place a stone at position currentPos
    gameInfo.isProcessing = true;
    await placeStone();
    gameInfo.currentPlayer = gameInfo.currentPlayer === 'white' ? 'black' : 'white';

    hideShadowStone();

    // generate an ia stone
    await placeIAStone();
    gameInfo.currentPlayer = gameInfo.currentPlayer === 'white' ? 'black' : 'white';
    showShadowStone();
    gameInfo.isProcessing = false;
}


const Board : React.FC<BoardProps> = ({
    label,
}) => {
    return (
        <div id='boardID' className='board' onClick={handleClick} onMouseMove={handleMouseMove} onMouseEnter={handleMouseEnter} onMouseLeave={handleMouseLeave}>
            <div id='shadow-stone' className='white-shadow-stone'></div>
        </div>
    );
}

export default Board;