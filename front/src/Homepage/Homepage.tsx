import './Homepage.css';
import ModeButton from './Components/ModeButton';

function Homepage() {
    return (
        <div className='home-master'>

            <h1 className='home-title'>GOMOKU</h1>
            <div className='homepage-buttons'>
                <ModeButton label='1 Player' route = '/GameIA'/>
                <ModeButton label='2 Player' route = '/GamePlayer'/>
            </div>

        </div>
    );
}

export default Homepage;