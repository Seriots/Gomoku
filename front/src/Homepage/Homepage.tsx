import './Homepage.css';
import ModeButton from './Components/ModeButton';

function Homepage() {
    return (
        <div className='home-master'>

            <h1 className='home-title'>GOMOKU</h1>
            <div className='homepage-buttons'>
                <ModeButton label='1 Player' route = '/gameIA'/>
                <ModeButton label='2 Player' route = '/player'/>
            </div>

        </div>
    );
}

export default Homepage;