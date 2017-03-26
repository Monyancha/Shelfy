import { HomeComponent } from './home/home.component';
import {ShelfieTrackerComponent} from './shelfie-tracker/shelfie-tracker.component';
import {NgModule} from '@angular/core';
import {AppComponent} from './app.component';
import { RouterModule, Routes } from '@angular/router';
import { MarketComponent } from "./market/market.component";

export const routes : Routes = [
    {
        path: 'tracker',
        component: ShelfieTrackerComponent
    }, {
        path: 'index',
        component: HomeComponent
    }, {
        path: 'market',
        component: MarketComponent,
    },{
        path: '**',
        redirectTo: '/index'
    }
]

@NgModule({
    imports: [RouterModule.forRoot(routes)],
    exports: [RouterModule]
})
export class AppRoutingModule {}