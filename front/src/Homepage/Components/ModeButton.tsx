import { useNavigate } from 'react-router-dom';
import './ModeButton.css';

interface ModeButtonProps {
	label: string,
    route: string,
}

const ModeButton : React.FC<ModeButtonProps> = ({
    label,
    route,
}) => {
    const navigate = useNavigate();
    return (
        <div className='mode-button-wrapper'>
            <button className='mode-button' onClick={() => {navigate(route)}}>{label}</button>
        </div>
    );
}

export default ModeButton;