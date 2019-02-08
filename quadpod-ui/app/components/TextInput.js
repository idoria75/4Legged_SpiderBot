import React from 'react'
import PropTypes from 'prop-types'
import styled, { css } from 'styled-components'

const Input = styled.input`
  
  color: var(--gray5);

  height: 48px;
  width: 100%;

  border: none;
  text-align: left;
  font-size: 14px;

  border-radius: 4px;
  border: 1px solid var(--gray3);
  
  padding: 5px;
  max-width: 200px;
  text-align: center;

  box-sizing: border-box;

  invalid {
    border-color: var(--danger);
  }
  ::placeholder {
    color: var(--gray7);
    opacity: 1;
  }
  :focus {
    outline: 1px solid var(--primary);
  }

  background: transparent;
`

function TextInput(props) {
  return <Input {...props} />
}

TextInput.propTypes = {
  icon: PropTypes.string,
  placeholder: PropTypes.string,
  disabled: PropTypes.bool,
  active: PropTypes.bool,
}

TextInput.defaultProps = {
  type: null,
  placeholder: '',
  icon: null,
  disabled: false,
  active: false,
}

export default TextInput