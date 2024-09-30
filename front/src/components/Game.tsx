import axios from 'axios';
import './Game.css';

function Game() {
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

	let color = 'white';
	const placeStone = async () => {
		const shadowStone = document.getElementById('shadow-stone');
		if (!shadowStone) {
			return;
		}
		const pos = computePositionFromPx(shadowStone.style.left, shadowStone.style.top);
		const listWhite = getPositionList(document.getElementsByClassName('white-stone'));
		const listBlack = getPositionList(document.getElementsByClassName('black-stone'));

		const res = await axios.get('http://localhost:6325/action/' + pos + '/' + color[0] + '/' + listWhite + '/' + listBlack + '//')
			.then((res) => {
				const board = document.getElementById('board');
				if (!board) {
					return;
				}
				let newStone = document.createElement('div');
				newStone.className = color + '-stone';
				newStone.style.left = shadowStone.style.left;
				newStone.style.top = shadowStone.style.top;
				board.appendChild(newStone);
				console.log(res.data);
				if (color === 'white') {
					color = 'black';
				} else {
					color = 'white';
				}
				shadowStone.className = color + "-shadow-stone";
			})
			.catch((err) => {
				console.log(err);
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
			</div>

		</div>
	);
}

export default Game;