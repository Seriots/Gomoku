import axios from 'axios';
import './Game.css';

function Test() {

    const callGame = () => {
        axios.get('http://localhost:6325/game')
            .then(res => {
                console.log(res.data);
            })
            .catch(err => {
                console.log(err);
            });
    }

    return (
		<div>
			<button onClick={callGame}> Call Game </button>
		</div>
	);
}

export default Test;