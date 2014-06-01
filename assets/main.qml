/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2
import QBookmarks 1.0

TabbedPane {
    id: tabbedPane
    property string getcommand
    property string gettitlebar
    getcommand: "http://"
    gettitlebar: "GET"
    showTabsOnActionBar: true
    Tab {
        id: getTab
        title: "REST"
        imageSource: "asset:///images/rest.png"
        delegate: Delegate {
            id: delegateGet
            source: "asset:///Get.qml"
        }
     
        delegateActivationPolicy: TabDelegateActivationPolicy.ActivateImmediately

    }
    
    Tab {
        id: bookmarksTab
        imageSource: "asset:///images/bookmarks.png"
        title: "Bookmarks"
        delegate: Delegate {
            id: delegateBookmarks
            source: "asset:///Bookmarks.qml"
        }
        delegateActivationPolicy: TabDelegateActivationPolicy.ActivateImmediately
    }

}