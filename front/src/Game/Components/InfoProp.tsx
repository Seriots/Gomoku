import './InfoBar.css';

import whiteStone from '../../assets/whiteStone.png';
import blackStone from '../../assets/blackStone.png';

interface InfoPropProps {
	title: string,
    value?: string,
    img?: string,
}

const InfoProp : React.FC<InfoPropProps> = ({
    title,
    value,
    img,
}) => {
    return (
        <div className='info-prop'>
            <h2>{title}</h2>
            {img && <img src={img === 'white' ? whiteStone : blackStone} alt='img'/>}
            {value && <p>{value}</p>}
        </div>
    );
}

export default InfoProp;