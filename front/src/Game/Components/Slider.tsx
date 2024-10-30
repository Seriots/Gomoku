import './Slider.css';

interface SliderProps {
    setter: React.Dispatch<React.SetStateAction<number>>,
    initial: number,
    min: number,
    max: number,
}

const Slider : React.FC<SliderProps> = ({
    setter,
    initial,
    min,
    max,
}) => {
    return (
      <input type="range" min={min} max={max} value={initial}
       onChange={(e) => setter(parseInt(e.target.value))}>
      </input>
    );
}

export default Slider;
