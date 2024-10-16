import axios from 'axios';
import './Game.css';

function Player() {

    const build_request = (base: string, lst: any) => {
        let res = base;
        for (let i = 0; i < lst.length; i++) {
            res += '/' + lst[i];
        }
        return res;
    }

	const computePositionFromPx = (x: string, y: string) => {
		const posX = (parseInt(x, 10) - 21) / 48;
		const posY = (parseInt(y, 10) - 21) / 48;
		return posX + posY * 19;
	}
	const getPositionList = (lst: any) => {
		let res = [];
		for (let i = 0; i < lst.length; i++) {
			res.push(computePositionFromPx(lst[i].style.left, lst[i].style.top));
		}
		return res.join(',');
	}

    const handleBackData = (res: any) => {
        const board = document.getElementById('board');
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

    
	let color = 'white';
    let is_processing = 0;
    let captured_count = {white: 0, black: 0};
    let end_game = false;

    const handleEndGame = (res: any, color: string) => {
        if (res.prevent_win.length !== 0) {
            const winner_text = document.getElementById('winner-text');
            if (winner_text) {
            winner_text.innerText = 'still alive';
            if (color === 'white')
                winner_text.style.color = 'white';
            else
                winner_text.style.color = 'black';
            }
        }
        else if (res.win_by_capture === 1 || (res.win_by_alignement === 1)) {
            const winner_text = document.getElementById('winner-text');
            if (winner_text) {
                winner_text.innerText = color + ' win';
                if (color === 'white')
                    winner_text.style.color = 'white';
                else
                    winner_text.style.color = 'black';
            }
            end_game = true;
        }
        else if (res.no_winner === 1) {
            const winner_text = document.getElementById('winner-text');
            if (winner_text) {
                winner_text.innerText = 'No winner';
                winner_text.style.color = 'grey';
            }
            end_game = true;
        }
    }

	const placeStone = async () => {
        if (is_processing > 0 || end_game)
            return;
		const shadowStone = document.getElementById('shadow-stone');
		if (!shadowStone)
			return;
		const pos = computePositionFromPx(shadowStone.style.left, shadowStone.style.top);

		const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
		const listBlack = getPositionList(document.getElementsByClassName('black-stone'));
		const listBlocked = getPositionList(document.getElementsByClassName('blocked-stone'));

        is_processing = is_processing + 1
		await axios.get(build_request('http://localhost:6325/action', [pos, color, listWhite, listBlack, listBlocked]))
			.then((res) => {
                console.log(res.data);
                if (res.data.error === undefined) {
                    handleBackData(res);
                    if (color === 'white')
                        captured_count.white += res.data.removed.length;
                    else
                        captured_count.black += res.data.removed.length;
                    handleEndGame(res.data, color);
                    color = color === 'white' ? 'black' : 'white';
                    shadowStone.className = color + "-shadow-stone";
                    console.log(captured_count);
                }
                is_processing = is_processing - 1
			})
			.catch((err) => {
				console.log(err);
                is_processing = is_processing - 1
			});

	}

	const handleMouseMove = (e: any) => {
		const x = e.clientX;
		const y = e.clientY;
		const nearestX = Math.floor(x / 48) * 48 + 21;
		const nearestY = Math.floor(y / 48) * 48 + 21;
		const shadowStone = document.getElementById('shadow-stone');
		if (shadowStone) {
			shadowStone.style.left = nearestX + 'px';
			shadowStone.style.top = nearestY + 'px';
		}
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

    return (
		<div className='game'>
			<div id='board' onClick={placeStone} onMouseMove={handleMouseMove} onMouseEnter={handleMouseEnter} onMouseLeave={handleMouseLeave}>
				<div id='shadow-stone' className='white-shadow-stone'></div>
                <p id="winner-text"></p>
			</div>
		</div>
	);
}

export default Player;