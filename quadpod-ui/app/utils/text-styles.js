import { css } from 'styled-components'

const title = css`
  font-size: 24px;
  font-weight: 600;
  color: var(--white);
`
const subtitle = css`
  font-size: 20px;
  font-weight: 600;
  color: var(--gray2);
`

const h1 = css`
  font-size: 18px;
  font-weight: 600;
  color: var(--white);
`

const h2 = css`
  font-size: 16px;
  font-weight: 500;
  color: var(--gray5);
`

const h3 = css`
  font-size: 14px;
  font-weight: 500;
  color: var(--gray4);
`

const normal = css`
  font-size: 14px;
  font-weight: 500;
  color: var(--gray3);
`

export default { title, subtitle, h1, h2, h3, normal }