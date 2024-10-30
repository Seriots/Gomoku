import { useEffect, useState } from 'react';
import './ParamsBar.css';

import Slider from './Slider';

interface OpeningRulesPropProps {
    openingRule: string,
    setOpeningRule: React.Dispatch<React.SetStateAction<string>>,
    gameRunning: boolean,
}

const OpeningRulesProp : React.FC<OpeningRulesPropProps> = ({
    openingRule,
    setOpeningRule,
    gameRunning,
}) => {
    const [ruleNumber, setRuleNumber] = useState(0);
    const openingRulesList = ['standard', 'swap', 'swap2', 'pro', 'longpro'];

    useEffect(() => {
        setOpeningRule(openingRulesList[ruleNumber]);
    }, [ruleNumber]);

    return (
      <div className='info-prop-slider'>
        <p >{openingRule}</p>
        {!gameRunning &&
          <Slider setter={setRuleNumber} initial={ruleNumber} min={0} max={openingRulesList.length - 1}/>
        }
      </div>
    );
}

export default OpeningRulesProp;
