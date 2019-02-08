import PropTypes from 'prop-types'
import styled from 'styled-components'

const Button = styled.button`

  height: 48px;
  
  min-width: 48x;

  display: flex;
  align-items: center;
  justify-content: center;

  border-radius: 30px;
  
  background-image: linear-gradient(68deg, var(--primary), #1effc3);
  box-shadow: 0 4px 9px rgba(0, 161, 255, 0.33);
  
  text-decoration: none;
  user-select: none;
  cursor: pointer;
  border: none;
  outline: 0;
  &:hover {
    -webkit-filter: brightness(90%);
    transition: all 0.1s ease;
  }

  &:active {
    -webkit-filter: brightness(70%);
    transition: all 0.1s ease;
  }

  &[disabled] {
    opacity: 0.5;
    cursor: not-allowed;
    pointer-events: none;
  }

  :after {
    content: '${({text}) => text}';
    font-family: Lato;
    font-size: 16px;
    font-weight: 600;
    color: white;
    margin: 0 8px;

    display: ${({icon}) => (icon ? 'none' : 'block')};
    margin: ${({icon}) => (icon ? '0' : '0 8px')};
  }

  :before{
    display: ${({icon}) => (icon ? 'block' : 'none')};
    content: '';
    float: left;
    width: 24px;
    height: 24px;
    background: rgba(19, 29, 42, 0.16) url("${({icon}) => icon}") no-repeat center center;
    background-size: 20px;
    border-radius: 50%;
    padding: 4px;
    margin-right: ${({icon}) => (icon ? '0' : '0 8px')};
  };
`

Button.defaultProps = {
  disabled: false,
}

Button.propTypes = {
  disabled: PropTypes.bool,
}

export default Button