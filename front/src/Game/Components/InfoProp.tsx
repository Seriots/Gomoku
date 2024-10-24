import './InfoBar.css';

interface InfoPropProps {
	title: string,
    value: string,
    img?: string,
}

const InfoProp : React.FC<InfoPropProps> = ({
    title,
    value,
}) => {
    return (
        <div className='info-prop'>
            <h2>{title}</h2>
            <p>{value}</p>
        </div>
    );
}

export default InfoProp;