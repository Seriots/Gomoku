import './ParamsBar.css';
import { Children } from 'react';


interface ParamsBarProps {
    children: any,
    labels: string[],
}

const ParamsBar : React.FC<ParamsBarProps> = ({
    children,
    labels,
}) => {
    return (
        <div className='params-bar'>
            <div className='param-props-div'>
            <span>
            {Children.map(children, (child, index) =>
                <div className='param-prop' key={index}>
                    <h2>{labels[index]}</h2>
                    {child}
                </div>
            )}
                
            </span>
            </div>
        </div>
    );
}

export default ParamsBar;