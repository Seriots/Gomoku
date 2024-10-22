import React from 'react';
import { Routes, Route } from 'react-router-dom';
import Game from './components/Game';
import Ia from './components/Ia';
import Player from './components/Player';
import Test from './components/Test';
import Homepage from './Homepage/Homepage';
import GameIA from './Game/GameIA';
import './App.css';

function App() {
	return (
		<div className="App">
			<Routes>
                <Route path="/" element={<Homepage />} />
                <Route path="/game" element={<Game />} />
                <Route path="/ia" element={<Ia />} />
                <Route path="/player" element={<Player />} />
                <Route path="/test" element={<Test />} />
                <Route path="/GameIA" element={<GameIA />} />

            </Routes>
		</div>
	);
}

export default App;
