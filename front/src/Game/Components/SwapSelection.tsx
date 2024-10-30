import React from 'react';

import whiteStone from '../../assets/whiteStone.png';
import blackStone from '../../assets/blackStone.png';

import './SwapSelection.css';

interface SwapSelectionProps {
	openingRule: string,
    setSwapChoice: any,
    setNeedSwapChoice: any,
}


const handleChoice = (choice: string, setSwapChoice: any, setNeedSwapChoice: any) => () => {
  setSwapChoice(choice);
  setNeedSwapChoice(false);
}

const SwapSelection : React.FC<SwapSelectionProps> = ({
  openingRule,
  setSwapChoice,
  setNeedSwapChoice,
}) => {
    return (
        <div className='swap-selection'>
          <p>make your choice</p>
          <div className='swap-selection-selection'>
            {openingRule === "swap" &&
              <React.Fragment>
                <img onClick={handleChoice("white", setSwapChoice, setNeedSwapChoice)}src={whiteStone} alt='img'/>
                <img onClick={handleChoice("black", setSwapChoice, setNeedSwapChoice)} src={blackStone} alt='img'/>
              </React.Fragment>
            }
            {openingRule === "swap2" &&
              <React.Fragment>
                <img onClick={handleChoice("white", setSwapChoice, setNeedSwapChoice)} src={whiteStone} alt='img'/>
                <img onClick={handleChoice("black", setSwapChoice, setNeedSwapChoice)} src={blackStone} alt='img'/>
                <p onClick={handleChoice("more", setSwapChoice, setNeedSwapChoice)}>+2</p>
              </React.Fragment>
            }
          </div>

        </div>
    );
}

export default SwapSelection;
