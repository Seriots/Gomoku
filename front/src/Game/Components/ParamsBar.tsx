import './ParamsBar.css';
import FirstPlayerProp from './FirstPlayerProp';


interface ParamsBarProps {
	setFirstPlayer: any,
}

const ParamsBar : React.FC<ParamsBarProps> = ({
    setFirstPlayer,
}) => {
    return (
        <div className='params-bar'>
            <div className='param-props-div'>
            <span>
                <FirstPlayerProp setFirstPlayer={setFirstPlayer}></FirstPlayerProp>
            </span>
            </div>
        </div>
    );
}

export default ParamsBar;