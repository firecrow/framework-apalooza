import { Component } from '@angular/core';

@Component({
  selector: 'angular-root',
  standalone: true,
  imports: [],
  template: `<h1>Hello world!</h1>`,
  styleUrls: ['./app.component.css'],
})
export class AppComponent {
  title = 'angular-app';
}
