import './Rules.css';

interface RulesButtonProps {
    setShowRules: any,
}

const RulesButton : React.FC<RulesButtonProps> = ({
    setShowRules,
}) => {
    return (
        <div className='rules-button-wrapper'>
            <button className='rules-button' onClick={() => {setShowRules(true)}}>Rules</button>
        </div>
    );
}

export default RulesButton;