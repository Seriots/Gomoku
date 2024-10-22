import './ParamsBar.css';

interface ParamsBarProps {
	label?: string,
}

const ParamsBar : React.FC<ParamsBarProps> = ({
    label,
}) => {
    return (
        <div className='params-bar'>
            <h1>Parameters</h1>
        </div>
    );
}

export default ParamsBar;