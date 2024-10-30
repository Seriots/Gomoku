import './ParamsBar.css';

import Slider from './Slider';

interface DepthPropProps {
    depth: number,
    setDepth: React.Dispatch<React.SetStateAction<number>>,
    gameRunning: boolean,
}

const DepthProp : React.FC<DepthPropProps> = ({
    depth,
    setDepth,
    gameRunning,
}) => {
    return (
      <div className='info-prop-slider'>
        <p >{depth}</p>
        {!gameRunning &&
          <Slider setter={setDepth} initial={depth} min={2} max={10}/>
        }
      </div>
    );
}

export default DepthProp;
