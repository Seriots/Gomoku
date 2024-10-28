import { GameInfoInterface } from '../GameIA';
import InfoProp from './InfoProp';
import './InfoBar.css';

interface InfoBarProps {
	gameInfo: GameInfoInterface,
}

const InfoBar : React.FC<InfoBarProps> = ({
    gameInfo,
}) => {
    return (
        <div className='info-bar'>
            <div className='info-props-div'>
                <span>
                    <InfoProp title={'Player'} img={gameInfo.currentPlayer}></InfoProp>
                    <InfoProp title={'White Capture'} value={gameInfo.whiteCapture.toString() + '/10'}></InfoProp>
                    <InfoProp title={'Black Capture'} value={gameInfo.blackCapture.toString() + '/10'}></InfoProp>
                </span>
                <span>
                    <InfoProp title={'Turn'} value={(Math.floor(gameInfo.currentRound / 2)).toString()}></InfoProp>
                    <InfoProp title={'Time'} value={gameInfo.processTime.toString()}></InfoProp>
                    <InfoProp title={'Depth'} value={gameInfo.processDepth.toString()}></InfoProp>
                </span>
            </div>
        </div>
    );
}

export default InfoBar;