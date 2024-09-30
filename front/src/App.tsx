import React from 'react';
import { Routes, Route } from 'react-router-dom';
import Game from './components/Game';
import Home from './components/Home';
import './App.css';

function App() {
	return (
		<div className="App">
			<Routes>
                <Route path="/" element={<Home />} />
                <Route path="/Game" element={<Game />} />
            </Routes>
		</div>
	);
}

export default App;
