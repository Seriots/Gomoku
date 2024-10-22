import './InfoBar.css';

interface InfoBarProps {
	label?: string,
}

const InfoBar : React.FC<InfoBarProps> = ({
    label,
}) => {
    return (
        <div className='info-bar'>
            <h1>Info</h1>
        </div>
    );
}

export default InfoBar;