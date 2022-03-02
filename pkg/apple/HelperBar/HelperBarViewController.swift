//
//  HelperBarViewController.swift
//  RetroArchiOS
//
//  Created by Yoshi Sugawara on 2/27/22.
//  Copyright © 2022 RetroArch. All rights reserved.
//

class HelperBarViewController: UIViewController {
   var viewModel = HelperBarViewModel()
   
   private let indicatorImageView: UIImageView = {
      let imageView = UIImageView(frame: .zero)
      imageView.image = UIImage(systemName: "arrow.down.circle")
      imageView.tintColor = .white
      imageView.translatesAutoresizingMaskIntoConstraints = false
      imageView.alpha = 0
      return imageView
   }()
   
   private let navigationBar: UINavigationBar = {
      let navBar = UINavigationBar()
      navBar.barTintColor = .black
      navBar.tintColor = .white
      navBar.isHidden = true
      return navBar
   }()
   
   override func viewDidLoad() {
      viewModel.delegate = self
      setupViews()
      setupBarItems()
   }
   
   override func viewDidAppear(_ animated: Bool) {
      DispatchQueue.main.asyncAfter(deadline: .now() + 0.5) { [weak self] in
         self?.showIndicatorAndFadeAway()
      }
   }
   
   override func viewDidLayoutSubviews() {
      super.viewDidLayoutSubviews()
      DispatchQueue.main.asyncAfter(deadline: .now() + 0.5) { [weak self] in
         self?.showIndicatorAndFadeAway()
      }
   }
   
   private func setupViews() {
      indicatorImageView.translatesAutoresizingMaskIntoConstraints = false
      view.addSubview(indicatorImageView)
      indicatorImageView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 4).isActive = true
      indicatorImageView.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
      indicatorImageView.heightAnchor.constraint(equalToConstant: 40).isActive = true
      indicatorImageView.widthAnchor.constraint(equalTo: indicatorImageView.heightAnchor).isActive = true
      view.addSubview(navigationBar)
      navigationBar.translatesAutoresizingMaskIntoConstraints = false
      navigationBar.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor).isActive = true
      navigationBar.leadingAnchor.constraint(equalTo: view.leadingAnchor).isActive = true
      navigationBar.trailingAnchor.constraint(equalTo: view.trailingAnchor).isActive = true
      let tap = UITapGestureRecognizer(target: self, action: #selector(didTap(_:)))
      tap.delegate = self
      view.addGestureRecognizer(tap)
      view.isUserInteractionEnabled = true
      navigationBar.delegate = self
   }
   
   private func setupBarItems() {
      let barButtonItems = viewModel.createBarButtonItems()
      let navItem = UINavigationItem()
      navItem.leftBarButtonItems = barButtonItems
      navigationBar.items = [navItem]
   }
   
   private func updateBarItems() {
      guard let navItem = navigationBar.items?[0],
            let barButtonItems = navItem.leftBarButtonItems else {
         return
      }
      for barButtonItem in barButtonItems {
         guard let helperBarItem = viewModel.barItemMapping[barButtonItem] else {
            continue
         }
         if helperBarItem.isSelected {
            barButtonItem.image = helperBarItem.selectedImage
         } else {
            barButtonItem.image = helperBarItem.image
         }
      }
   }
   
   private func showIndicatorAndFadeAway() {
      UIView.animateKeyframes(withDuration: 5.0, delay: 0) {
         UIView.addKeyframe(withRelativeStartTime: 0, relativeDuration: 4/5) { [weak self] in
            self?.indicatorImageView.alpha = 1.0
         }
         
         UIView.addKeyframe(withRelativeStartTime: 1/3, relativeDuration: 1/5) { [weak self] in
            self?.indicatorImageView.alpha = 0.0
         }
      }
   }

   @objc func didTap(_ sender: UIGestureRecognizer) {
      viewModel.didInteractWithBar = true
   }
}

extension HelperBarViewController: UIGestureRecognizerDelegate {
   func gestureRecognizer(_ gestureRecognizer: UIGestureRecognizer, shouldRecognizeSimultaneouslyWith otherGestureRecognizer: UIGestureRecognizer) -> Bool {
      true
   }
}

extension HelperBarViewController: HelperBarViewModelDelegate {
   func setNavigationBarHidden(_ isHidden: Bool) {
      navigationBar.isHidden = isHidden
   }
   func updateNavigationBarItems() {
      updateBarItems()
   }
}

extension HelperBarViewController: UINavigationBarDelegate {
   func position(for bar: UIBarPositioning) -> UIBarPosition {
      return .topAttached
   }
}
