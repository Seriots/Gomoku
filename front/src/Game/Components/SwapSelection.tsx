import React from 'react';

import whiteStone from '../../assets/whiteStone.png';
import blackStone from '../../assets/blackStone.png';

import './SwapSelection.css';

interface SwapSelectionProps {
	openingRule: string,
}

const SwapSelection : React.FC<SwapSelectionProps> = ({
  openingRule,
}) => {
    return (
        <div className='swap-selection'>
          <p>make your choice</p>
          <div className='swap-selection-selection'>
            {openingRule === "swap" &&
              <React.Fragment>
                <img src={whiteStone} alt='img'/>
                <img src={blackStone} alt='img'/>
              </React.Fragment>
            }
            {openingRule === "swap2" &&
              <React.Fragment>
                <img src={whiteStone} alt='img'/>
                <img src={blackStone} alt='img'/>
                <p>+2</p>
              </React.Fragment>
            }
          </div>

        </div>
    );
}

export default SwapSelection;
