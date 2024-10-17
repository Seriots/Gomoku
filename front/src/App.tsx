import React from 'react';
import { Routes, Route } from 'react-router-dom';
import Game from './components/Game';
import Ia from './components/Ia';
import Player from './components/Player';
import Home from './components/Home';
import Test from './components/Test';
import './App.css';

function App() {
	return (
		<div className="App">
			<Routes>
                <Route path="/" element={<Home />} />
                <Route path="/game" element={<Game />} />
                <Route path="/ia" element={<Ia />} />
                <Route path="/player" element={<Player />} />
                <Route path="/test" element={<Test />} />
            </Routes>
		</div>
	);
}

export default App;
