import './ParamsBar.css';


interface ActivateHintPropProps {
    activateHint: boolean,
	setActivateHint: any,
    gameRunning: boolean,
    id: string,
}

const handleClick = (activateHint: boolean, setActivateHint: any, gameRunning: boolean, id: string) => () => {
    if (gameRunning)
        return;
    const activateHintIMG = document.getElementById('activateHintID' + id) as HTMLElement;
    if (!activateHintIMG)
        return;
    activateHintIMG.classList.toggle('activate');
    setActivateHint(!activateHint);
}

const ActivateHintProp : React.FC<ActivateHintPropProps> = ({
    activateHint,
	setActivateHint,
    gameRunning,
    id,
}) => {
    return (
        <div>
            <div className='activate-hint-wrapper'>
                <button id={'activateHintID' + id} className='activate-hint' onClick={handleClick(activateHint, setActivateHint, gameRunning, id)}></button>
            </div>
        </div>
    );
}

export default ActivateHintProp;