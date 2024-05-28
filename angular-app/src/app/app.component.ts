import { Component } from '@angular/core';

@Component({
  selector: 'angular-root',
  standalone: true,
  imports: [],
  template: `<input value="hello from angular" />`,
  styleUrls: ['./app.component.css'],
})
export class AppComponent {
  title = 'angular-app';
}
