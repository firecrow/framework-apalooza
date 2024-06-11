import {TestSet} from './test_runner';
import {InitStartModel} from './data';

const calcBasicSet = new TestSet({
    func: () => {
        const model = InitStartModel();
        console.log(JSON.stringify(model));
    },
    cases: [0]
});

calcBasicSet.run();