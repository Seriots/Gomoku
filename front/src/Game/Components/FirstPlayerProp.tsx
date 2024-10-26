import './ParamsBar.css';


interface FirstPlayerPropProps {
    firstPlayer: string,
	setFirstPlayer: any,
    gameRunning: boolean,
}

const handleClick = (firstPlayer: string, setFirstPlayer: any, gameRunning: boolean) => () => {
    if (gameRunning)
        return;
    const firstPlayerIMG = document.getElementById('firstPlayerID') as HTMLElement;
    const whiteText = document.getElementById('WhiteTextID') as HTMLElement;
    const blackText = document.getElementById('BlackTextID') as HTMLElement; 
    if (!firstPlayerIMG || !whiteText || !blackText)
        return;
    firstPlayerIMG.classList.toggle('black');
    whiteText.classList.toggle('toggle');
    blackText.classList.toggle('toggle');

    firstPlayer === 'white' ? setFirstPlayer('black') : setFirstPlayer('white');
}

const FirstPlayerProp : React.FC<FirstPlayerPropProps> = ({
    setFirstPlayer,
    firstPlayer,
    gameRunning,
}) => {
    return (
        <div>
            <div className='first-player-selector-wrapper'>
                <p id='WhiteTextID' className='first-player-selector-white'>player</p>
                <button id='firstPlayerID' className='first-player-selector' onClick={handleClick(firstPlayer, setFirstPlayer, gameRunning)}></button>
                <p id='BlackTextID' className='first-player-selector-black'>computer</p>
            </div>
        </div>
    );
}

export default FirstPlayerProp;