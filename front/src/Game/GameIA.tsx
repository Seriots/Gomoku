import Board from './Components/Board';
import InfoBar from './Components/InfoBar';
import ParamsBar from './Components/ParamsBar';
import './GameIA.css';

function GameIA() {
    return (
        <div className='gameIA-master'>
            <ParamsBar />
            <Board />
            <InfoBar />
        </div>
    );
}

export default GameIA;