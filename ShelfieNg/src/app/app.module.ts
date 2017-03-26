import { AppRoutingModule } from './app-routing.module';
import { AngularFireModule } from 'angularfire2';
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';

import { AppComponent } from './app.component';
import { ShelfieTrackerComponent } from './shelfie-tracker/shelfie-tracker.component';
import { HomeComponent } from './home/home.component';
import { MarketComponent } from './market/market.component';


// Must export the config
export const firebaseConfig = {
  apiKey: 'AIzaSyCkER-Uj4lU5EfZq8J-MmNl_J5qlRP7r3Q',
  authDomain: 'shelfie-cc23e.firebaseapp.com',
  databaseURL: 'https://shelfie-cc23e.firebaseio.com/',
  // storageBucket: '<your-storage-bucket>',
  // messagingSenderId: '<your-messaging-sender-id>'
};

@NgModule({
  declarations: [
    AppComponent,
    ShelfieTrackerComponent,
    HomeComponent,
    MarketComponent
  ],
  imports: [
    BrowserModule,
    AngularFireModule.initializeApp(firebaseConfig),
    FormsModule,
    HttpModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
