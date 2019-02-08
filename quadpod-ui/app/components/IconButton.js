import styled, { css } from 'styled-components'

const IconButton = styled.button`
  border: none;
  cursor: pointer;
  outline: 0;
  height: ${({size}) => size || '30px'};
  width: ${({size}) => size || '30px'};

  // Alternative that allows one to change the icon color
  background-color: ${({color}) => color || 'var(--gray7)'};
  -webkit-mask-image: url("${({icon}) => icon}");
  mask-image: url("${({icon}) => icon}");
  mask-size: 100%;

  background-size: 90%;

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

  position: relative;

  ${({badge, badgeColor}) =>
    badge &&
    css`
      :after {
        content: attr(data-badge);
        position: absolute;
        top: 2px;
        right: 0px;
        font-size: 0.7em;
        background: ${badgeColor || 'var(--primary)'};
        color: white;
        width: 8px;
        height: 8px;
        text-align: center;
        border-radius: 50%;
        box-shadow: 0 1px 4px rgba(0, 161, 255, 0.53);
      }
    `}
`
export default IconButton