import './StartButton.css';

interface StartButtonProps {
	gameRunning: boolean,
    setGameRunning: any,
}

const handleClick = (gameRunning: boolean, setGameRunning: any) => (e: any) => {
    if (gameRunning === false) {
        setGameRunning(true);
    }
}

const StartButton : React.FC<StartButtonProps> = ({
    gameRunning,
    setGameRunning,

}) => {
    return (
        <div>
            <button className="start-button" onClick={handleClick(gameRunning, setGameRunning)}></button>
        </div>
    );
}

export default StartButton;