import './ParamsBar.css';

import whiteStone from '../../assets/whiteStone.png';
import blackStone from '../../assets/blackStone.png';

interface FirstPlayerPropProps {
	setFirstPlayer: any,
}

const handleClick = (setFirstPlayer: any) => () => {
    const firstPlayer = document.getElementById('firstPlayerID') as HTMLElement;
    if (!firstPlayer)
        return;
    firstPlayer.classList.toggle('black');
    if (firstPlayer.innerHTML === 'white') {
        setFirstPlayer('black');
        firstPlayer.innerHTML = 'black';
    } else {
        setFirstPlayer('white');
        firstPlayer.innerHTML = 'white';
    }
}

const FirstPlayerProp : React.FC<FirstPlayerPropProps> = ({
    setFirstPlayer,
}) => {
    return (
        <div className='param-prop'>
            <h2>First player</h2>
            <button id='firstPlayerID' className='first-player-selector' onClick={handleClick(setFirstPlayer)}></button>
        </div>
    );
}

export default FirstPlayerProp;