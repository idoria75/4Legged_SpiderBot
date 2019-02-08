import PropTypes from 'prop-types'
import styled from 'styled-components'

import TextStyles from '../utils/text-styles'

const Text = styled.span`
  display: block;
  font-family: Lato;
  ${({type}) => TextStyles[type]};
`

Text.propTypes = {
  type: PropTypes.string,
  color: PropTypes.string,
}

Text.defaultProps = {
  type: 'normal',
  color: 'white',
}

export default Text