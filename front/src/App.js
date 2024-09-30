import './App.css';
import axios from 'axios';
import { useEffect, useState } from 'react';



function App() {

	const test = async () => {
		const res = await axios.get('http://localhost:6325/game');
		console.log(res.data);
	}

  	return (
		<div className="App">
				<h1>hello world</h1>
				<button onClick={test}>test</button>
		</div>
	);
}

export default App;
