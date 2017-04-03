import { timeout } from 'rxjs/operator/timeout';
import {Observable} from 'rxjs/Rx';
import {Http} from '@angular/http';
import {AngularFire} from 'angularfire2';
import {FirebaseListObservable, FirebaseObjectObservable} from 'angularfire2/database';
import {Component, OnInit} from '@angular/core';

@Component({selector: 'app-shelfie-tracker', templateUrl: './shelfie-tracker.component.html', styleUrls: ['./shelfie-tracker.component.scss']})
export class ShelfieTrackerComponent implements OnInit {

  item0_0 : string;
  item0_1 : string;
  item0_2 : string;
  item1_0 : string;
  item1_1 : string;
  item1_2 : string;

  liveImage : string = "http://10.0.150.149:5000/getImage";

  items : FirebaseObjectObservable < any[] >;
  constructor(af : AngularFire, public http : Http) {
    this.items = af
      .database
      .object('/realtime/bottles');
    this
      .items
      .subscribe(result => {
        this.item0_0 = ""
        this.item0_1 = "";
        this.item0_2 = "";
        this.item1_0 = "";
        this.item1_1 = "";
        this.item1_2 = "";
        for (var key in result) {
          var element = result[key];
          switch (key) {
            case "0_0":
              this.item0_0 = element;
              break;
            case "0_1":
              this.item0_1 = element;
              break;
            case "0_2":
              this.item0_2 = element;
              break;
            case "1_0":
              this.item1_0 = element;
              break;
            case "1_1":
              this.item1_1 = element;
              break;
            case "1_2":
              this.item1_2 = element;
              break;
          }
        }
      })
  }

  ngOnInit() {
  
  }

  capture(){
      this.liveImage = "http://10.0.150.149:5000/getImage?" + new Date().getTime();
  }

}
