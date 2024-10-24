import './ParamsBar.css';
import FirstPlayerProp from './FirstPlayerProp';


interface ParamsBarProps {
    firstPlayer: string,
	setFirstPlayer: any,
    gameRunning: boolean,
}

const ParamsBar : React.FC<ParamsBarProps> = ({
    firstPlayer,
    setFirstPlayer,
    gameRunning,
}) => {
    return (
        <div className='params-bar'>
            <div className='param-props-div'>
            <span>
                <FirstPlayerProp firstPlayer={firstPlayer} setFirstPlayer={setFirstPlayer} gameRunning={gameRunning} ></FirstPlayerProp>
            </span>
            </div>
        </div>
    );
}

export default ParamsBar;