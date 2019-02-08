import styled from 'styled-components'

export default styled.ul`
  height: 90%;

  overflow: hidden;
  overflow-y: auto;
  
  ::-webkit-scrollbar {
    background: transparent;
    width: 4px;
    height: 4px;
  }

  ::-webkit-scrollbar-button {
    display: none;
  }

  ::-webkit-scrollbar-track {
    background-color: transparent;
  }

  ::-webkit-scrollbar-track-piece {
    background-color: transparent;
  }

  ::-webkit-scrollbar-thumb {
    background-color: #ececf0;
    border-radius: 2px;
  }

  ::-webkit-scrollbar-corner {
    display: none;
  }

  ::-webkit-resizer {
    display: none;
  }
`