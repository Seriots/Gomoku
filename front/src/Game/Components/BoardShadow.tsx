import { useEffect } from 'react';
import './Board.css';

interface BoardShadowProps {
	gameRunning: boolean,
    winner: string,
    setWinner: any,
}

const BoardShadow : React.FC<BoardShadowProps> = ({
    gameRunning,
    winner,
    setWinner
}) => {
    useEffect(() => {
        if (winner === '')
            return ;

        const board_shadow = document.getElementById('boardShadowID');
        const end_game_text = document.getElementById('endGameTextID');
        const shadow_master = document.getElementById('shadowMasterID');
        if (!board_shadow || !end_game_text || !shadow_master)
            return;

        shadow_master.style.zIndex = '1';
        board_shadow.classList.add('show');
        end_game_text.innerText = winner + ' win';
        end_game_text.classList.add('show');

    }, [winner]);

    useEffect(() => {
        if (gameRunning !== true)
            return;
        
        const board_shadow = document.getElementById('boardShadowID');
        const end_game_text = document.getElementById('endGameTextID');
        const shadow_master = document.getElementById('shadowMasterID');
        if (!board_shadow || !end_game_text || !shadow_master)
            return;

        shadow_master.style.zIndex = '0';
        end_game_text.innerText = '';
        board_shadow.classList.remove('show');
        end_game_text.classList.remove('show');
        setWinner('');

    }, [gameRunning]);

    return (
        <div id='shadowMasterID' className='board-shadow-master'>
            <div id='boardShadowID' className='board-shadow'></div>
            <p id='endGameTextID' className='end-game-text'></p>
        </div>
    );
}

export default BoardShadow;