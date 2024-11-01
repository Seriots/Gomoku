import './Homepage.css';
import ModeButton from './Components/ModeButton';
import RulesButton from './Components/RulesButton';
import { useState } from 'react';
import RulesScreen from './Components/RulesScreen';

function Homepage() {

    const [showRules, setShowRules] = useState(false);

    return (
        <div className='home-master'>

            <h1 className='home-title'>GOMOKU</h1>
            <div className='homepage-buttons'>
                <ModeButton label='1 Player' route = '/GameIA'/>
                <ModeButton label='2 Player' route = '/GamePlayer'/>
            </div>
            <RulesButton setShowRules={setShowRules}></RulesButton>
            {showRules && 
                RulesScreen({setShowRules: setShowRules})
            }
        </div>
    );
}

export default Homepage;