import './Rules.css';

interface RulesScreenProps {
    setShowRules: any,
}

const RulesScreen : React.FC<RulesScreenProps> = ({
    setShowRules,
}) => {
    return (
        <div className='rules-screen-wrapper'>
            <div className='rules-screen'>
                <h1><i><u>GOMOKU Rules :</u></i></h1>
                <p> This is a gomoku game with the Pente variant played on a 19 x 19 goban board</p>
                <h2> There are two win conditions: </h2>
                <p>The first player to align 5 stones horizontally, vertically or diagonally wins the game if no stone of this alinement can be captured</p>
                <p>The first player to capture ten opponent stones win. To capture opponent stones, you need to enclose two and ONLY two stone by two of your own stone, if this append, enclosed stone are removed from the board</p>
                <h2> Other rules: </h2>
                <p>You play only one stone at the time, in two player mode you need to switch the mouse at each turn</p>
                <p>A free-three is an alignement of three stone that if it is no blocked instantly, necessarily leads to an alignment of 5 stone. You are not allowed to create two free-   three at the same time, except by capturing </p>
                <p>There is no stone limit, you can play as many stones as you want</p>
                <p>There is no time limit, you can take your time to think</p>

            </div>
            <button className='rules-button' onClick={() => {setShowRules(false)}}>Close</button>
        </div>
    );
}

export default RulesScreen;