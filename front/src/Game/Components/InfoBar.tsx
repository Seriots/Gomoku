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
            <h1>Info</h1>
            <div className='info-props-div'>
                <span>
                    <InfoProp title={'Player'} value={gameInfo.currentPlayer}></InfoProp>
                    <InfoProp title={'White Cap'} value={gameInfo.whiteCaptured.toString() + '/10'}></InfoProp>
                    <InfoProp title={'Black Cap'} value={gameInfo.blackCaptured.toString() + '/10'}></InfoProp>
                </span>
                <span>
                    <InfoProp title={'Turn'} value={gameInfo.currentRound.toString()}></InfoProp>
                    <InfoProp title={'Time'} value={gameInfo.processTime.toString()}></InfoProp>
                    <InfoProp title={'Depth'} value={gameInfo.processDepth.toString()}></InfoProp>
                </span>
            </div>
        </div>
    );
}

export default InfoBar;