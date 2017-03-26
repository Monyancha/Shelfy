import { ShelfieNgPage } from './app.po';

describe('shelfie-ng App', () => {
  let page: ShelfieNgPage;

  beforeEach(() => {
    page = new ShelfieNgPage();
  });

  it('should display message saying app works', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('app works!');
  });
});
