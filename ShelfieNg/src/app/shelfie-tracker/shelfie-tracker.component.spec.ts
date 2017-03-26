import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ShelfieTrackerComponent } from './shelfie-tracker.component';

describe('ShelfieTrackerComponent', () => {
  let component: ShelfieTrackerComponent;
  let fixture: ComponentFixture<ShelfieTrackerComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ShelfieTrackerComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ShelfieTrackerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
